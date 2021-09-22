// spoj -gss1 ---- maximum subarray sum problem without update operation
const int maxn = 5e4 + 10;
struct node{
	ll sum,pref,suff,ans;
};

node t[4*maxn];
ll a[maxn];

node combine(node left_node,node right_node)
{
	node curr;
	curr.sum = left_node.sum + right_node.sum;
	curr.pref = max(left_node.pref,left_node.sum + right_node.pref);
	curr.suff = max(right_node.suff,right_node.sum + left_node.suff);
	curr.ans = max(max(left_node.ans,right_node.ans),left_node.suff+right_node.pref);
	return curr; 
}

void build(int nd,int l,int r)
{
	if(l==r)
	{
		t[nd].sum = a[l];
		t[nd].pref = a[l];
		t[nd].suff = a[l];
		t[nd].ans = a[l];
		return;
	}

	int mid = l + (r-l)/2;
	build(2*nd+1,l,mid);
	build(2*nd+2,mid+1,r);
	t[nd] = combine(t[2*nd+1],t[2*nd+2]);
}

node query(int nd,int l,int r,int tl,int tr)
{
	if(l>tr||r<tl)
	{
		node res;
		res.sum = 0;
		res.pref = INT_MIN;
		res.suff = INT_MIN;
		res.ans = INT_MIN;
		return res;
	}

	if(l>=tl&&r<=tr)
	{
		return t[nd];
	}

	int mid = l + (r-l)/2;
	return combine(query(2*nd+1,l,mid,tl,tr),query(2*nd+2,mid+1,r,tl,tr));
}




